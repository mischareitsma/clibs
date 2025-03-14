
// Stolen from http://www.cse.yorku.ca/~oz/hash.html, answer in
// https://stackoverflow.com/questions/7666509/hash-function-for-string/45641002
unsigned long hash(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}