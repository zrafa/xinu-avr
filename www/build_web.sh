
markdown_py -f index.html $1
echo '<br><br><hr><small> last edit: '$(date)' - <i>Rafael Ignacio Zurita (rafa at fi.uncoma.edu.ar)</i></small> <br><br>' > /tmp/deleteme2
cat w1.html index.html /tmp/deleteme2 w2.html | grep -v "visit the Xinu" > /tmp/deleteme.html
rm index.html
rm /tmp/deleteme2
mv /tmp/deleteme.html ../index.html
