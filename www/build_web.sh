
markdown_py -f index.html $1
echo '<br><br><hr><small><i> last edit: '$(date)' - Rafael Ignacio Zurita (rafa at fi.uncoma.edu.ar)</i></small> <br><br>' > /tmp/deleteme2
cat w1.html index.html /tmp/deleteme2 w2.html | grep -v "Visit its Web" | grep -v 'xinu-avr</h1>' | grep -v "=====" > /tmp/deleteme.html
rm index.html
rm /tmp/deleteme2
mv /tmp/deleteme.html ../index.html
