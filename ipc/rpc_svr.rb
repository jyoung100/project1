
require "xmlrpc/server"

class Svr
	def addnumbers(a,b)
		puts "#{a}+#{b}=#{a+b}...yay RPC!"
		return a+b;
	end
end

server = XMLRPC::Server.new( 1234 )
server.add_handler( 'testsvr', Svr.new )
server.serve