#ifndef _DEFINES_HPP
#define _DEFINES_HPP 1

#if (SFML_VERSION_MAJOR == 2)
	#if (SFML_VERSION_MINOR < 3)
		typedef unsigned int numeric_t;
	#else
		typedef std::size_t numeric_t;
	#endif

	#if (SFML_VERSION_MINOR < 4)
		#define _setFillColor(c)	setColor(c)
	#else
		#define _setFillColor(c)	setFillColor(c)
	#endif
#endif

#endif