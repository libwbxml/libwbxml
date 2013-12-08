#! -e

echo 
echo "##### Initialize svn2git directory #####"
echo 

# setup a fresh directory
rm -rf svn2git
mkdir svn2git
cd svn2git

echo 
echo "##### Basic SVN to GIT migration #####"
echo 

# convert without branches and tags
svn2git http://svn.opensync.org/libwbxml/wbxml2 -v -m

# cleanup useless branch
git branch -r -d svn/libwbxml-0.10.x

# convert without branches and tags
svn2git http://svn.opensync.org/libwbxml/wbxml2 -v -m

echo 
echo "##### add migration script to git #####"
echo 

# 0. checkout master
# 1. branch svn2git migration
# 2. checkout new branch
# 3. add migration script
# 4. commit migration script
# 5. checkout master

git checkout master
git branch svn2git
git checkout svn2git
cp ../convert2git.sh .
git add convert2git.sh
git commit -m "Added script for SVN to GIT conversion." convert2git.sh
git checkout master

echo 
echo "##### fix releases #####"
echo 

#for tag in `git branch -r | grep -v '@' | grep -v trunk`; do
# for tag in `git tag | grep -v '@' | grep -v '0.9.2' | grep -v '0.9.3'`; do
for tag in `git tag | grep -v '@'`; do
    echo
    echo Fixing: $tag ...

    echo -e \\t Checkout $tag ...
    git checkout --quiet $tag

    echo -n -e \\t Checking for existing branch ...
    COMMITS=`git log --all --grep="libwbxml/wbxml2/tags/$tag" | grep "libwbxml/wbxml2/tags/$tag" | sed 's;.*@;;g' | sed 's;\s.*;;g' | wc -l`
    if test $COMMITS -gt 1 -o "$tag" = "0.9.2" -o "$tag" = "0.9.3"; then 
        echo " branch detected."
        echo -n -e \\t "=> Sanitizing branch ..."
        git checkout --quiet -b svn-release-$tag $tag;
        echo " done."
        continue;
    fi
    echo " no branch."
    echo -e \\t "=> Fix necessary."

    echo -n -e \\t Determining svn revision of branch point ...
    TAG_REVISION=`git log --all --grep="libwbxml/wbxml2/tags/$tag" | grep "libwbxml/wbxml2/tags/$tag" | sed 's;.*@;;g' | sed 's;\s.*;;g'`
    TAG_COMMIT=`git log --all --grep="libwbxml/wbxml2/tags/$tag\@${TAG_REVISION}" | grep commit | sed 's;commit ;;'`
    echo $TAG_COMMIT at $TAG_REVISION

    echo -n -e \\t Determining branch point ...
    BRANCH_COMMIT=
    BRANCH_REVISION=$TAG_REVISION
    # lookup for last available SVN revision (for 0.10.0, 0.10.1, 0.10.9)
    while test -z "$BRANCH_COMMIT" -a $BRANCH_REVISION -gt 0;do 
        ## echo -e \\t\\t Testing branch point $BRANCH_REVISION
        BRANCH_COMMIT=`git log --all --grep="trunk\@${BRANCH_REVISION}" | grep commit | sed 's;commit ;;'`
        ((BRANCH_REVISION--))
    done
    ((BRANCH_REVISION++))
    echo -e $BRANCH_COMMIT at $BRANCH_REVISION

    # rebase local branch (single revision) to branch commit
    echo -e \\t Rebasing release to branch
    # 1. checkout release and create a branch with a single commit
    echo -e \\t\\t Checkout and branch single isolated release
    git checkout --quiet -b svn-release-$tag $tag
    # 3. rebase release to branch point
    echo -e \\t\\t Rebase single isolated release
    git rebase --quiet --onto $BRANCH_COMMIT master
    # 4. move the tag
    git tag -d $tag
    git tag $tag

    echo -e \\t Fixed.
done;

echo
echo "##### added SVN references hard to GIT repository ######"
echo

git checkout master

# adding tests to master

git checkout svn-release-libwbxml-0.11.2 tests
git commit -m "Imported the tests from libwbxml-0.11.2. Fixing SVN:externals." tests

# adding cmake/modules

cd cmake
git checkout svn-release-libwbxml-0.11.2 modules
git commit -m "Imported the cmake modules from libwbxml-0.11.2. Fixing SVN:externals." modules
cd ..

echo
echo "##### Please push the repository. #####"
echo

git remote add origin git@github.com:libwbxml/libwbxml.git
git push -u --all origin -f
git push --tags origin

# the end ;-)

cd ..

exit 0;
