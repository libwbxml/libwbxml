#!@PERL_PROGRAM@

# Copyright (C) 2009 Michael Bell <michael.bell@opensync.org>

use strict;
use warnings FATAL => qw( all );
use English;

# check params
# 1. original file
# 2. new file
# 3. no more params

my $ignore_attribute = "";
if ($ARGV[0] eq "--delete-attribute") {
	shift;
	die "The attribute which must be deleted is missing."
		if (not $ARGV[0]);
	$ignore_attribute = shift;
}

die "There must be two arguments (old and new file)."
	if (scalar(@ARGV) != 2);

my $org_filename = $ARGV[0];
my $new_filename = $ARGV[1];

die "The original file does not exist."
	if (not $org_filename or not -e $org_filename);

die "The new file is not valid filename."
	if (not $new_filename);

die "The new file exists already."
	if (-e $new_filename);

# open files

die "The original file is not readable."
	if (not open(my $ORG_FD, "<", $org_filename));

die "The new file is not writeable."
	if (not open(my $NEW_FD, ">", $new_filename));

# look for the XML tree
#   - version and encoding
#   - DTD
#   - XML tree

my $line = <$ORG_FD>;

my $state = "IGNORE";
do {
    ## determine state

    ## XML detection
    if ($state eq "IGNORE" and $line =~ q{^\s*<[a-zA-Z]}) {
	$state = "XML_TREE";
    }

    ## version and encoding detection
    if ($state eq "IGNORE" and $line =~ q{^\s*<\?}) {
        $state = "ENC_OPEN";
    }
    if ($state eq "ENC_OPEN" and $line =~ q{^\s*<\?.*\?>\s*$} and $line !~ q{\sencoding="[^"]*"}) {
	# add default encoding
	$line =~ s{\s*\?>\s*$}{ encoding="UTF-8"?>\n};
    }
    if ($state eq "ENC_OPEN" and $line =~ q{\?>\s*$}) {
	## uppercase encoding
	my $encoding = $line;
	$encoding =~ s{.*\sencoding="([^"]*)".*}{$1};
	$encoding = uc($encoding);
	$line =~ s{\sencoding="[^"]*"}{ encoding="${encoding}"};
        $state = "WRITE";
    }

    ## DTD detection
    if ($state eq "IGNORE" and $line =~ q{^\s*<!DOCTYPE}) {
        $state = "DTD_OPEN";
    }
    if ($state eq "DTD_OPEN" and $line =~ q{\s\[<\?.*\?>\]}) {
	## such special XML stuff is lost in WBXML
	$line =~ s{\s\[<\?.*\?>\]}{};
    }
    if ($state eq "DTD_OPEN" and $line =~ q{>\s*$}) {
        $state = "WRITE";
    }

    ## comment detection
    if ($state eq "IGNORE" and $line =~ q{^\s*<!--}) {
	$state = "COMMENT_OPEN";
    }
    if ($state eq "COMMENT_OPEN" and $line =~ q{-->\s*$}) {
	$state = "IGNORE";
    }

    ## handle data
    if ($state eq "IGNORE") {
	$line = <$ORG_FD>;
    }
    if ($state eq "WRITE") {
	$line =~ s{[\s\r\n]*$}{\n}s;
	print $NEW_FD $line;
	$line = <$ORG_FD>;
	$state = "IGNORE";
    }
    if ($state =~ q{_OPEN$}) {
	$line .= <$ORG_FD>;
	$line =~ s{\s*[\n\r]+\s*}{ }sg;
	$line .= "\n";
    }
} while ($state ne "XML_TREE");

# XML tree state
#   - element
#      <
#      element name
#      blank
#      attribute name
#      = attribute assignment
#      attribute value
#      >
#   - data
#   - comment

my $indent = 0;
my $char = "";
my $text = "";
my $element = "";
my $expected = "";
$state = "NEUTRAL";
while (1) {
    ## $line works line oriented
    ## but the parser works character oriented
    last if (not defined $line);
    if (length ($line) == 0) {
	$line = <$ORG_FD>;
	last if (not defined $line or length($line) < 1);
    }
    $char = substr($line, 0, 1);
    $line = substr($line, 1);

    # check state

    # reset text state
    if ($state eq "TEXT_NEWLINE" and $char !~ q{[\s\n\r]}) {
	$state = "NEUTRAL";
    }

    # ignore leading blanks (normalization)
    if ($state eq "NEUTRAL" and $char =~ q{\s}) {
	next;
    }

    # handle comment or element which starts in a text line
    if ($state eq "TEXT" and $char eq "<") {
        if (length($expected)) {
            # the original text must be replaced for test validation
            $text = $expected;
            $expected = "";
        }
	$text =~ s{\s*$}{};
	print $NEW_FD "${text}\n";
	$state = "NEUTRAL";
    }

    # try to handle a new comment or element
    if ($state eq "NEUTRAL" and $char eq "<") {
        # let's look forward (element or comment)
	die "A standalone smaller than "<" sign is not allowed in XML."
        	if (length($line) < 1);
	$char = substr($line, 0, 1);
	$line = substr($line, 1);
	if ($char eq "!") {
	    if ($line =~ q{^--}) {
		## this should be a comment
		$char = substr($line, 0, 2);
		$line = substr($line, 2);
		$state = "COMMENT";
                $text = "";
	    } elsif ($line =~ q{^\[CDATA\[}) {
		## CDATA section detected
		for (my $i = 0; $i < $indent; $i++) {
		    print $NEW_FD "  ";
		}
		print $NEW_FD "<![CDATA[";
		$line =~ s{^\[CDATA\[}{};
		$state = "CDATA";
	    } else {
		die "Only comments and CDATA sections are supported and not with '<!${line}'."
		    if ($char ne "--");
	    }
	} elsif ($char =~ q{[a-zA-Z]}) {
	    ## this is an element
	    for (my $i = 0; $i < $indent; $i++) {
		print $NEW_FD "  ";
	    }
	    $indent++;
	    print $NEW_FD "<".$char;
	    $element = $char;
	    $state = "ELEMENT";
	} elsif ($char eq "/") {
	    ## this is a closing element
	    $indent--;
	    for (my $i = 0; $i < $indent; $i++) {
		print $NEW_FD "  ";
	    }
	    print $NEW_FD "</";
	    $state = "ELEMENT";
	} else {
            ## this is illegal
	    die "A smaller than "<" sign must be a tag or a comment.";
        }
	next;
    }

    # ignore comments
    if ($state eq "COMMENT") {
	if ($char eq "-" and substr($line, 0, 2) eq "->") {
	    # end of comment
	    $line = substr($line, 2);
	    $state = "NEUTRAL";
            # check if this is a special action configuration
            if ($text =~ m{^\sEXPECTED\s::=\s.*\s$}) {
                # This is the value for the next text data.
                $expected = $text;
		$expected =~ s{^\sEXPECTED\s::=\s(.*)\s$}{$1};
                $text = "";
            }
	} else {
            $text .= $char;
        }
	next;
    }

    # read and write text data
    if ($state eq "NEUTRAL" and $char ne "<") {
	# new text data
	for (my $i = 0; $i < $indent; $i++) {
	    print $NEW_FD "  ";
        }
	$text = $char;
        $state = "TEXT";
	next;
    }
    if ($state eq "TEXT" and $char eq "\r") {
	next;
    }
    if ($state eq "TEXT" and $char eq "\n") {
	$text =~ s{\s*$}{};
	print $NEW_FD "${text}\n";
	$state = "TEXT_NEWLINE";
	next;
    }
    # if & is not handled as &amp; then this error cannot be recovered
    if ($state eq "TEXT" and $char eq '"') {
	$text .= "&quot;";
	next;
    }
    if ($state eq "TEXT" and $char eq "'") {
	$text .= "&apos;";
	next;
    }
    if ($state eq "TEXT" and $char eq '<') {
	$text .= "&lt;";
	next;
    }
    if ($state eq "TEXT" and $char eq '>') {
	$text .= "&gt;";
	next;
    }
    if ($state eq "TEXT") {
	$text .= $char;
	next;
    }
    if ($state eq "TEXT_NEWLINE" and $char =~ q{\s\r\n}) {
	next;
    }

    # read element name
    if ($state eq "ELEMENT" and $char =~ q{[a-zA-Z0-9_]}) {
	print $NEW_FD $char;
	$element .= $char;
	next;
    }

    # detect space for potential attribute
    if ($state eq "ELEMENT" and $char =~ q{[\s\r\n]}) {
	$state = "POTENTIAL_ATTRIBUTE";
        next;
    }

    # detect and read attribute
    if ($state eq "POTENTIAL_ATTRIBUTE" and $char =~ q{[a-zA-Z0-9_]}) {
	if ($ignore_attribute and
	    substr($ignore_attribute, 0, 1) eq $char and
	    substr($ignore_attribute, 1) eq substr($line, 0, length(substr($ignore_attribute, 1))))
	{
	    # let's ingore the attribute
	    $line =~ s{^[a-zA-Z_1-9]*=}{};
	    if (substr($line, 0, 1) eq "'") {
		$line =~ s{^'[^']*'}{};
	    } else {
		$line =~ s{^"[^"]*"}{};
	    }
	    next;
	}
	$state = "ATTRIBUTE_NAME";
	print $NEW_FD " ";
    }
    if ($state eq "ATTRIBUTE_NAME" and $char =~ q{[a-zA-Z0-9_]}) {
	print $NEW_FD $char;
	next;
    }
    if ($state eq "ATTRIBUTE_NAME" and $char eq "=") {
	print $NEW_FD $char;
	$state = "ATTRIBUTE_ASSIGN";
        next;
    }
    if ($state eq "ATTRIBUTE_ASSIGN" and $char eq '"') {
	print $NEW_FD $char;
	$state = "ATTRIBUTE_VALUE_QUOT";
        next;
    }
    if ($state eq "ATTRIBUTE_VALUE_QUOT" and $char ne '"') {
	print $NEW_FD $char;
	next;
    }
    if ($state eq "ATTRIBUTE_VALUE_QUOT" and $char eq '"') {
	print $NEW_FD $char;
        $state = "POTENTIAL_ATTRIBUTE";
	next;
    }
    if ($state eq "ATTRIBUTE_ASSIGN" and $char eq "'") {
	print $NEW_FD $char;
	$state = "ATTRIBUTE_VALUE_APOS";
        next;
    }
    if ($state eq "ATTRIBUTE_VALUE_APOS" and $char ne "'") {
	print $NEW_FD $char;
	next;
    }
    if ($state eq "ATTRIBUTE_VALUE_APOS" and $char eq "'") {
	print $NEW_FD $char;
        $state = "POTENTIAL_ATTRIBUTE";
	next;
    }

    # handle standalone element
    if (($state eq "ELEMENT" or $state eq "POTENTIAL_ATTRIBUTE")
        and $char eq "/")
    {
	# consume the closing ">" and add the complete closing tag
	$char = ">";
	$line =~ s{^\s*>}{};
	$indent--;
	print $NEW_FD ">\n";
	for (my $i = 0; $i < $indent; $i++) {
	    print $NEW_FD "  ";
	}
	print $NEW_FD "</${element}>\n";
	$state = "NEUTRAL";
	next;
    }

    # read element end
    if (($state eq "ELEMENT" or $state eq "POTENTIAL_ATTRIBUTE")
        and $char eq ">")
    {
	print $NEW_FD $char."\n";
	$state = "NEUTRAL";
	next;
    }

    # handle CDATA
    if ($state eq "CDATA" and $char eq "]" and substr($line , 0, 2) eq "]>") {
	$line = substr($line, 2);
	print $NEW_FD "]]>\n";
	$state = "NEUTRAL";
	next;
    }
    if ($state eq "CDATA") {
	print $NEW_FD $char;
	next;
    }
};

# close files

close $ORG_FD;
close $NEW_FD;
