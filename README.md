# BSQ

BSQ means find the biggest square. The objective of the subject is to find the first largest possible square<br>
in the map (represent by 2 characters '.' For the void and 'o' for obstacles)
> See subject: B-CPE-110_BSQ.pdf

# Requires
## Commands
* make
* gcc
* gcovr
## Dependencies
* criterion

# Makefile Recipes
* all / bsq
> To compile the program.
* clean
> To delete temporary files.
* fclean
> To delete temporary files and executables.
* re
> Delete temporary files and executables and compile the program.
* mouli
> Test if the whole program works on the test maps provided in the topic.
* tests_run
> Run unit tests
* coverage
> Allows you to see the coverage processed by unit tests.
