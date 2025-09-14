**!!! FIRST BIBLE NIV VERSION IN PLAIN TEXT RIGHT IN THIS REPO !!!**
# What was this supposed to be for
- In memory of King Terry
- Large massive functionality considering it's in a terminal
- To worship God

# Setup
- Either download a bin or compile the code from the source
    - How to compile?
        - ```make && ./bible_cli/Binaries/bible_cli```
- Launch ```ch``` bash file with args to create bible.conf file with ***language*** and ***translation*** params.
Example of usage: ```./ch en kjv```.
- Hooray. The file was created.
- Make sure ```languages.lconf``` is not empty/deleted. Otherwise the program won't launch. Also make sure you specified right translation.
- Turn off **the debug mode** if you don't need it.
    - Find ```#define DEBUG_MODE 1``` in ```Bible-CLI-lite/bible_cli/Headers/tool.h``` and change the value to ```0```.

# FAQ
### — So, how can I make it?
### — Well, how can I download new translations for the Bible?
**Answer:** You can download texts only in the OpenBible format.
- Download a text file from OpenBible.
- Rename it considering the file format ```<LANGUAGE>_<TRANSLATION>.bbl```.
- Move this file into ```Bible-CLI-lite/Translations/```
- Change ```Bible-CLI-lite/bible.conf``` by using ```ch``` utility like above.
### — What if I've got a non-OpenBible format?
**Answer:** you *should* write your own parser. How to do that? Go right to ```Bible-CLI-lite/bible_cli/Sources/``` and recreate a file named ```parser.c``` from the scratch. You have to use the same function names and structs that is declared in the ```parser.h``` file. Now it's fine. You can use the program with your own format.

# Licence?
There is no licence, and all that rubbish, just because the Bible doesn't need it. You can modify the code however you can and however you want.

# Sources
The primary source is OpenBible. [Check out the Bible's translations](https://openbible.com/textfiles).

# Thanks them
* [Terry Davis for the motivation](https://www.youtube.com/watch?v=oH41gGBVpkE)
<img width="320" height="180" alt="17575743962221808125180978607495" src="https://github.com/user-attachments/assets/51c17f5d-0fad-48e1-b2a4-298818731757" /> <br />
