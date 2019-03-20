.PHONY: all
all: thesis.pdf

thesis.pdf: thesis.tex introduction.tex alice-in-wonderland.tex appendix-1.tex

%.pdf: %.tex
	pdflatex $*
	bibtex $*
	pdflatex $*
	pdflatex $*

.PHONY: clean
clean:
	rm -f *.{dvi,ps,log,aux,bbl,blg,lof,lot,toc}

