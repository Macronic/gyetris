#ifndef INI_H_DEFINED
#define INI_H_DEFINED

#include <string>
#include <cstdio>                // FILE* fopen() fclose()
#include <iniparser/iniparser.h> // dictionary*

/// Loads settings from a file with `.ini` configuration format.
///
/// ## Usage
///
///     INI ini;
///
///     if (! ini.load("filename.ini"))
///         // Woops, something bad happened.
///         // File doensn't exist, whatever
///
///     bool var = ini.get("section1:booleanValue", true);
///
///     int otherVar = ini.get("section2:intValue", 2);
///
///     std::string another = ini.get("section3:string", "4");
///
/// ## get() path format
///
/// Suppose you have an ini file like this:
///
///     [section1]
///     key = value
///
///     [section2]
///     otherKey = 2
///
/// Then to get() the first value you should ask with the
/// string "section1:key".
/// For the second, it should be "section2:otherKey".
///
class INI
{
public:
	INI();
	virtual ~INI();

	/// Loads and parses #file.
	///
	/// @return If we've successfuly loaded the file.
	bool load(std::string file);

	/// Cleans up internal allocated memory.
	///
	/// @note It is safe to call this function many times,
	///       and it's automatically called at the destructor
	///       so call it only if you want to release the
	///       memory early.
	///
	void free();

	/// Gets a boolean value located at #where inside the file.
	/// Check the class documentation for it's format.
	///
	/// @return The value or #default_value if it doesn't exist,
	///         the file itself isn't there or something happened.
	bool get(std::string where, bool default_value);

	/// Gets an integer value located at #where inside the file.
	/// Check the class documentation for it's format.
	///
	/// @return The value or #default_value if it doesn't exist,
	///         the file itself isn't there or something happened.
	int get(std::string where, int default_value);

	/// Gets a double value located at #where inside the file.
	/// Check the class documentation for it's format.
	///
	/// @return The value or #default_value if it doesn't exist,
	///         the file itself isn't there or something happened.
	double get(std::string where, double default_value);

	/// Gets a string value located at #where inside the file.
	/// Check the class documentation for it's format.
	///
	/// @return The value or #default_value if it doesn't exist,
	///         the file itself isn't there or something happened.
	std::string get(std::string where, const char* default_value);

	/// Gets a string value located at #where inside the file.
	/// Check the class documentation for it's format.
	///
	/// @return The value or #default_value if it doesn't exist,
	///         the file itself isn't there or something happened.
	std::string get(std::string where, std::string default_value);

	/// Saves all internal ini key-values to #file.
	///
	/// @note No comments are preserved when saving!
	void save(std::string file);

	/// C-style saving of the internal ini key-values.
	///
	/// @note The advantage of it is that you can specify
	///       stdout or stderr.
	/// @note It checks for NULL pointers, don't worry.
	/// @note Again, no comments are preserved when saving!
	void save(FILE* file);

private:

	/// Iniparser's internal data structure.
	dictionary* ini;
};

#endif //INI_H_DEFINED
