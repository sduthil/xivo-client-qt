/* LICENSE NOTICE
	Copyright (c) 2008, Frederick Emmott <mail@fredemmott.co.uk>

	Permission to use, copy, modify, and/or distribute this software for any
	purpose with or without fee is hereby granted, provided that the above
	copyright notice and this permission notice appear in all copies.

	THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
	WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
	MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
	ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
	WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
	ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
	OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
#ifndef _JSONQT_JSON_TO_PROPERTIES_H
#define _JSONQT_JSON_TO_PROPERTIES_H

#include "ParseException.h"
#include "JsonQtExport.h"

#include <QObject>
#include <QString>

namespace JsonQt
{
	/** Class for setting the properties of a QObject from a JSON string.
	 * Note that this only pays attention to basic types in the top level
	 * object in the JSON.
	 *
	 * @author Fred Emmott <mail@fredemmott.co.uk>
	 */
	class JSONQT_EXPORT JsonToProperties
	{
		public:
			/** Main parsing function.
			 *
			 * @param json is a string containing JSON text.
			 * @param object is an object with properties to be
			 * 	filled from JSON.
			 * @throws ParseException if the string provided is not
			 * 	valid JSON (or at least this parser thinks it
			 * 	isn't ;) )
			 */
			void parse(const QString& json, QObject* object)
				throw(ParseException);
	};
}

#endif