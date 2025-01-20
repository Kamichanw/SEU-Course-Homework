\documentclass{article}
\usepackage{tikz}
\usetikzlibrary{automata, positioning}

\begin{document}

\begin{tikzpicture}[shorten >=1pt, node distance=2cm, on grid, auto]
   \node[state, initial] (q0)   {$0$};
   \node[state] (q1) [above right=of q0] {$1$};
   \node[state] (q2) [right=of q1] {$2$};
   \node[state] (q3) [below right=of q0] {$3$};
   \node[state] (q4) [right=of q3] {$4$};
   \node[state, accepting] (q5) [below right=of q4] {$5$};

   \path[->]
   (q0) edge node {$a$} (q1)
        edge node [swap] {$b$} (q3)
   (q1) edge node {$c$} (q2)
   (q3) edge node {$d$} (q4)
   (q4) edge node {$e$} (q5);
\end{tikzpicture}

\end{document}