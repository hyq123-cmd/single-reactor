execute_file_server = server.out
execute_file_client	= client.out
object_file = main.o reactor.o threadpool.o
link_library = pthread

all: $(execute_file_server) $(execute_file_client)

edit:
	vim $(source_name)

$(execute_file_server):	$(object_file)
	g++ -std=c++11  $(object_file) -o $(execute_file_server) -l $(link_library)

main.o:	main.cpp
	g++ -std=c++11 -c main.cpp -o main.o

reactor.o:	reactor.cpp
	g++ -std=c++11 -c reactor.cpp -o reactor.o

threadpool.o:	threadpool.cpp
	g++ -std=c++11 -c threadpool.cpp -o threadpool.o
	
$(execute_file_client): client.cpp
	g++ -std=c++11 client.cpp -o $(execute_file_client) 

run:
	./$(execute_file_server)

clean:
	rm -f $(execute_file_server) $(object_file) $(execute_file_client)
