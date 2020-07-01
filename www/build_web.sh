
markdown_py -f index.html $1
cat w1.html index.html w2.html > /tmp/deleteme.html
rm index.html
mv /tmp/deleteme.html ../index.html
