/*
 * MIT License
 *
 * Copyright(c) 2011-2020 The Maintainers of Nanvix
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <nanvix/ulib.h>

#include <posix/stdlib.h>

/* Import definitions. */
extern const char *grep(const char *text, const char *pattern);

/**
 * @brief Greps a pattern.
 */
char *sed(
	const char *text,
	char *newtext,
	const char *pattern,
	const char *newpattern
)
{
	char *pnewtext = newtext;
	int patternlen = ustrlen(pattern);
	int newpatternlen = ustrlen(newpattern);
	int textlen = ustrlen(text);

	/*
	 * FIXME: the new pattern should not be longer the old pattern.
	 */
	if (newpatternlen > patternlen)
		return (newtext);

	for (const char *ptext = text; ptext < (text + textlen); /* noop*/)
	{
		size_t n;
		const char *base;
	   
		base = grep(ptext, pattern);

		if (base == NULL)
			base = text + textlen;

		n = base - ptext;
		umemcpy(pnewtext, ptext, n);

		ptext += n;
		pnewtext += n;

		if (textlen - ((pnewtext - newtext)) >= newpatternlen)
			umemcpy(pnewtext, newpattern, newpatternlen);

		ptext += patternlen;
		pnewtext += newpatternlen;
	}

	return (newtext);
}
