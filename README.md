# spell-autocorrector

Type text you want autocorrected into `text_to_check.txt` then compile and run `./main` which will
replace spelling errors in the text file

It uses a bloom filter to check whether each word is spelt correctly and if not then finds
the closest word that is valid to replace it with
