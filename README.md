### README for Project 3: Page Rank

---

#### Overview

This project is an implementation of the PageRank algorithm in C. PageRank is an algorithm used to rank web pages in search engine results, originally developed by Larry Page and Sergey Brin at Google. The algorithm calculates the relevance of each page in a network based on the links it receives from other pages.

In this project, we simulate a random surfer model and use Markov chains to compute the PageRank of each vertex (web page) in a directed graph, which represents the structure of the web.

---

#### Features

1. **Random Surfer Model**:
   - Simulates a random surfer browsing the web to approximate the PageRank of each page.
   - The surfer either follows a link from the current page or jumps to a random page if they get bored.

2. **Markov Chain Approach**:
   - Uses matrix multiplication to accurately calculate the PageRank values.
   - Computes the stationary distribution of the Markov chain, which represents the long-term probability of the surfer being on each page.

3. **Command Line Interface**:
   - Supports various options for running the program, including:
     - `-r N`: Simulate N steps of the random surfer and output the result.
     - `-m N`: Simulate N steps of the Markov chain and output the result.
     - `-s`: Compute and print statistics of the graph.
     - `-p P`: Set the boredom probability to P%.
     - `-h`: Print a brief overview of the available command line parameters.

---

#### Installation

1. **Prerequisites**:
   - A C compiler supporting C11 standard.
   - Make sure you have `make` installed on your system.

2. **Compilation**:
   - Clone the repository and navigate to the project directory.
   - Run the following command to compile the program:
     ```bash
     make
     ```
   - This will generate an executable binary named `pagerank`.

---

#### Usage

```bash
./pagerank [OPTIONS]... [FILENAME]
```

- **Options**:
  - `-r N`: Simulate N steps of the random surfer.
  - `-m N`: Simulate N steps of the Markov chain.
  - `-s`: Compute and print statistics of the graph.
  - `-p P`: Set the boredom probability (default is 10%).
  - `-h`: Display help message.

- **Example**:
  ```bash
  ./pagerank -r 1000 -p 15 input_graph.dot
  ```
  This command will simulate 1000 steps of the random surfer with a boredom probability of 15% on the graph defined in `input_graph.dot`.

---

#### Project Structure

- **src/**: Contains the source code files (`.c` and `.h`).
- **Makefile**: Build instructions for the project.
- **README.md**: This file, explaining the project.

---

#### License

This project is licensed under the University of Saarlandes
