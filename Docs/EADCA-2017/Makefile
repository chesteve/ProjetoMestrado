default: all

all:
	- make pdf
	- make clean

pdf:
	- pdflatex -shell-escape -synctex=1 -interaction=nonstopmode "main".tex
	- bibtex main
	- pdflatex -shell-escape -synctex=1 -interaction=nonstopmode "main".tex
	- pdflatex -shell-escape -synctex=1 -interaction=nonstopmode "main".tex
	- mv main.pdf EADCA-2017.pdf

clean:
	- rm -rfv *.aux
	- rm -rfv *.bbl *.blg *.glo *.idx *.lof *.log *.lot *.synctex.gz *.toc \
		 *.acn *.ist *.mw *.gz 

clean-all:
	- rm -rfv *.aux
	- rm -rfv *.bbl *.blg *.glo *.idx *.lof *.log *.lot *.synctex.gz *.toc \
		 *.acn *.ist *.mw *.gz *.pdf



