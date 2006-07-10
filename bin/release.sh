#! /bin/bash
#
# release.sh: make a libwbxml release
#
# USAGE: release.sh tagname
#
# Note: tagname may be HEAD to just grab the head revision
#

SVNROOT='http://libwbxml.aymerick.com:8080/repo/wbxml2/trunk'

if test $# != 1; then
  echo "USAGE: $0 tagname"
  exit 1
fi

tmpdir=wbxml2-release.$$
if test -e $tmpdir; then
  echo "ERROR: oops. chose the $tmpdir subdir, but it exists."
  exit 1
fi

echo "Checking out into temporary area: $tmpdir"
svn co -q -r "$1" "$SVNROOT" $tmpdir || exit 1

# figure out the release version
vsn="`$tmpdir/bin/version.sh $tmpdir/src/wbxml.h`"

echo ""
echo "Release version: $vsn"

if test "$1" = HEAD ; then
  distdir=wbxml2-`date '+%Y-%m-%d'`
else
  distdir=wbxml2-$vsn
fi

if test -e $distdir; then
  echo "ERROR: for safety, you must manually remove $distdir."
  rm -rf $tmpdir
  exit 1
fi

mkdir $distdir || exit 1

echo ""
echo "----------------------------------------------------------------------"
echo "Building $distdir based on the MANIFEST:"
files="`sed -e 's/[ ]:.*$//' $tmpdir/MANIFEST`"
for file in $files; do
  echo "Copying $file..."
  (cd $tmpdir && cp $CPOPTS $file ../$distdir) || exit 1
done

echo ""
echo "----------------------------------------------------------------------"
echo "Removing (temporary) checkout directory..."
rm -rf $tmpdir

tarball=$distdir.tar.gz
echo "Constructing $tarball..."
tar cf - $distdir | gzip -9 > $tarball || exit $?
rm -r $distdir

echo "Done."