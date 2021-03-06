MiningMail
==========

Experiments (graph algorithms, text mining, machine learning) with email datasets.

My main intent is to explore some data analisys over email datasets. To keep this work practical I´ll be using the famous Enron´s email dataset. You can get it at  https://www.cs.cmu.edu/~enron/. There are 517.424 email files. I think it is a good start to play with classical graph algorithms to answer some interesting (IMHO) questions: "Is this email intrinsic urgent?", "Which employees are 'Celebrities' (http://www.geeksforgeeks.org/the-celebrity-problem/) ?", "Whats is the mean connection degree of all company?", "Whats is the 'CEO Number' (like the Erdős Number)" and so on.

My (first) outline for this project is:

1) Develop some basic code to load messages from file and filter relevant information (e.g., if I just want non-stop words from emails labeled 'URGENT')
2) Use Boost Graph Library to work in a higher level of abstraction http://www.boost.org/doc/libs/1_55_0/libs/graph/doc/index.html
3) Solve some problems (even hardcoded) that I think should interesting to a email database owner ("How can a company can idendify which users are leaking classified emails"? ).


Some 'collateral' that I expected:
1) Validate Netbeans as C++11 IDE.
2) Produce useful code using Boost.
3) Deal with performance issues. As we have more than 500k messages in 2,15GB, it can be a good start.
4) Develop some skills to apply graph algorithms to social data.

Please contact me if you are interested in this kind of stuff: wesleymesquita@gmail.com.



