# MySQL randstr

This little project serves two purposes: to create an efficient random
string generator, the output of which will be used to create salt
strings for the [Schema Framework](https://www.github.com/cjungmann/SchemaFramework),
replacing the drop-salt protocol that is clumsy and inflexible.

The second purpose is to document the process for creating a MySQL UDF
(User-Defined Function) on Linux.  This project is quite simple, with
little complexity getting in the way of a demonstration of the fundamentals
of creating and installing a UDF.

## Creating the Library

This project runs like some older you-build-it projects by calling the
following commands:
- ./configure
- make
- sudo make install

The install target copies the shared library file to the plugin_lib,
then DROP IS EXIST the function before CREATE FUNCTION to load the function.

The CREATE FUNCTION is called without specifying a database, and it then seems
to be available in all databases.  It doesn't seem like it should work this
way, but the installation and usage makes this assumption until I learn how
and why this might not be the case.

## Installation Test

This UDF will eventually be needed for all SchemaFramework installations.
For servers that host multiple SchemaFramework applications, it shouldn't
be necessary to reinstall this UDF, but there is no way that I can detect
whether or not stored function has been loaded.  I can see if the library
exists in the plugins directory, but the existence of the library does not
ensure that it is being used by a stored function.
