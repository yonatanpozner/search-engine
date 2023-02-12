CXX=g++
CC=$(CXX)

CXXFLAGS = -std=c++17 -Wall -pedantic -Wextra

CPPFLAGS = 	-I configuration/ -I application/
CPPFLAGS += -I crawler/ -I indexer/ 
CPPFLAGS += -I index/ 
CPPFLAGS += -I searcher/ 
CPPFLAGS += -I pagerank/web_graph/ -I pagerank/pagerank/ -I pagerank/pagerank_factory/
CPPFLAGS += -I safe_queue/ -I safe_unordered_set/
CPPFLAGS += -I search_io/
CPPFLAGS += -I text_parser/ -I url_parser/ 
CPPFLAGS += -I safe_synchronization/

OBJECTS = main.o 
OBJECTS += configuration/fileloader.o application/application.o
OBJECTS += crawler/crawler.o indexer/indexer.o 
OBJECTS += text_parser/text_parser.o url_parser/url_parser.o
OBJECTS += index/index.o 
OBJECTS += searcher/searcher.o 
OBJECTS += safe_synchronization/safe_synchronization.o
OBJECTS += search_io/terminal_search_io.o search_io/network_search_io.o
OBJECTS += pagerank/web_graph/web_graph.o pagerank/pagerank/pagerank.o pagerank/pagerank_factory/pagerank_factory.o

LDLIBS = -lcurl -lcurlpp -lgumbo -lsfml-network

run: main
	./main


pagerank/pagerank_factory/pagerank_factory.o: pagerank/web_graph/web_graph.hpp pagerank/pagerank/pagerank.hpp
search_io/network_search_io.o: searcher/searcher.hpp
search_io/terminal_search_io.o: searcher/searcher.hpp
searcher/searcher.o: index/index.hpp pagerank/pagerank/pagerank.hpp
indexer/indexer.o: index/index.hpp
crawler/crawler.o: text_parser/text_parser.hpp url_parser/url_parser.hpp \
 				safe_synchronization/safe_synchronization.hpp \
				indexer/indexer.hpp pagerank/web_graph/web_graph.hpp \
				pagerank/pagerank_factory/pagerank_factory.hpp 
application/application.o: crawler/crawler.hpp search_io/terminal_search_io.hpp search_io/network_search_io.hpp
configuration/fileloader.o: configuration/configuration.hpp
main.o: configuration/fileloader.hpp configuration/configuration.hpp \
		index/index.hpp indexer/indexer.hpp text_parser/text_parser.hpp \
		url_parser/url_parser.hpp safe_unordered_set/safe_unordered_set.hpp \
		safe_queue/safe_queue.hpp crawler/crawler.hpp searcher/searcher.hpp \
		search_io/terminal_search_io.hpp search_io/network_search_io.hpp \
		application/application.hpp pagerank/web_graph/web_graph.hpp \
		pagerank/pagerank/pagerank.hpp pagerank/pagerank_factory/pagerank_factory.hpp \
		safe_synchronization/safe_synchronization.hpp 


main: $(OBJECTS) $(LDLIBS)

clean:
	@$(RM) $(OBJECTS)  */*.o  *.o main
