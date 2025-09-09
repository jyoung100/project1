require "xmlrpc/client"

#create client object, and tell it where to find
#  the server
client = XMLRPC::Client.new( "localhost", "/", 1234 )

#make a remote call
s = client.call('testsvr.addnumbers',67, 4)
print "Result from remote add: #{s}"

