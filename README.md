# External Indexer

An indexer implementation on secondary memory using an inverted index structure. The main memory available is set by the user and the sorting process is done by External Quicksort algorithm.

Ps. Before executing the program, make sure that in the executable directory exists a folder named "tmp". This is necessary for the intermediate steps of the sorting process. Something similar is done in the tests directory for simple tests named "toys". To run these tests, generate the executable file with the command "make" in the main directory and then execute the script named "toys.sh", located in the directory "tests/toys".

Read the [doc](res/doc.pdf) and the [spec](res/spec.pdf) for more information.
