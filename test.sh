./bin/Server &
FOO_PID=$!

#echo "Server PID: $FOO_PID"
./bin/Client

# do other stuff
kill $FOO_PID
