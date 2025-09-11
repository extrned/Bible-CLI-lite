**!!! FIRST BIBLE NIV VERSION IN PLAIN TEXT RIGHT IN THIS REPO !!!**
# What was this supposed to be for
- In memory of King Terry
- Large massive functionality considering it's in a terminal
- To worship God

# FAQ
### — So, how can I make it?
**Answer:** Simple as that, mate. Use ```make``` to build the project and then run the executable.
### — Well, how can I download new translations for the Bible?
**Answer:** It's easy as well.
- Download any text file with the plain text of the Bible (NO JSON/XML/ET CETERA FORMATS).
- Rename it considering the file format ```<LANGUAGE>_<TRANSLATION>.bbl```.
- Move this file into ```Bible-CLI-lite/Translations/```
- Change ```Bible-CLI-lite/bible.conf``` by replacing the value of the translation and the language **OR** do the same using ```Bible-CLI-lite/ch``` (which is a bash script): ```./ch <language> <translation>``` (the file also **must** be in the *.bbl* format)
### — What if I've got a non-OpenBible format?
**Answer:** you *should* write your own parser. How to do that? Go right to ```Bible-CLI-lite/bible_cli/Sources/``` and recreate a file named ```parser.c``` from the scratch. You have to use the same function names that is declared in the ```parser.h``` file. Now it's fine. You can use the program with your format.

# Licence?
There is no licence, and all that rubbish, just because the Bible doesn't need it. You can modify the code however you can and however you want.

# Sources
The primary source is OpenBible. [Check out the Bible's translations](https://openbible.com/textfiles).

# Thanks them
* [Terry Davis for the motivation](https://www.youtube.com/watch?v=oH41gGBVpkE)
<img width="320" height="180" alt="17575743962221808125180978607495" src="https://github.com/user-attachments/assets/51c17f5d-0fad-48e1-b2a4-298818731757" /> <br />
