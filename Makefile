#all: quickref.html quickref-cards.html install.html programming.html book.html

%.html: %.adoc
	asciidoctor -a reproducible -b html -r asciidoctor-bibtex  -a allow-uri-read $<

# asciidoctor-latex -a reproducible -a linkcss -a stylesheet=colony.css -a stylesdir=astylesheets/stylesheets -b html -r asciidoctor-bibtex  -a allow-uri-read $<


index.html: index.adoc
	asciidoctor-latex -b html -a reproducible -a linkcss -a stylesheet! $<

book.html: book.adoc $(shell find . -type f)
math.html: math.adoc $(shell find . -type f)
install.html: install.adoc $(shell find 01-installation/ 02-docker -type f)
programming.html: programming.adoc $(shell find 06-programming 07-quickref -type f)
quickref-cards.html: quickref-cards.adoc $(shell find 07-quickref -type f)
quickref.html: quickref.adoc $(shell find 07-quickref -type f)
modeling.html: modeling.adoc $(shell find 03-modeling 04-learning 05-applications -type f)

serve:
	bundle exec jekyll serve

clean:
	rm book.html math.html install.html programming.html quickref.html quickref-cards.html modeling.html
