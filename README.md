# Sydney Friedland
## CS50 Winter 2020, Tiny Search Engine

TSE is a modular search engine comprised of a [Crawler](crawler/README.md), which crawls a finite domain of webpages internal to a Dartmouth CS department server, an [Indexer](indexer/README.md), which parses the crawled pages and writes the indexed information to a file, and a [Querier](querier/README.md), which takes a user query from the command line, searches the index, and outputs pages ranked by the frequency of the search terms.

See each component's README for more information. 

I wrote the code in the `common`, `crawler`, `indexer`, and `querier` directories. In [TSE-datastructures-temp](https://github.com/sfriedland21/TSE-datastructures-temp), I also wrote separate implementations of the counterset (counters), set, and hashtable data structures in `libcs50`.

*Run on a Linux system or server.*

To build, run `make`.

To clean up, run `make clean`.
