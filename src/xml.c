/*
 * xml.c
 *
 *  Created on: 30-dec.-2016
 *      Author: wdedul01
 */

#include <string.h>
#include <libxml/parser.h>
#include <libxml/xinclude.h>

int xmlProcess(char *xml_string) {

#ifdef LIBXML_XINCLUDE_ENABLED
	xmlDocPtr doc;

	/*
	 * this initialize the library and check potential ABI mismatches
	 * between the version it was compiled for and the actual shared
	 * library used.
	 */
	LIBXML_TEST_VERSION
	/*
	 * parse include into a document
	 */
	doc = xmlReadMemory(xml_string, strlen(xml_string), "include.xml", NULL, 0);

	if (doc == NULL) {
		return 1;
	}

	/*
	 * Free the document
	 */
	xmlFreeDoc(doc);

	/*
	 * Cleanup function for the XML library.
	 */
	xmlCleanupParser();
	/*
	 * this is to debug memory for regression tests
	 */
	xmlMemoryDump();
	return 0;
#else
	return 1;
#endif
}
