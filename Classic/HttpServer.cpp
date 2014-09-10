int HTTPSocket::get_request_len(const char *s, int buf_len) {
	const unsigned char *buf = (unsigned char *) s;
	int i;

	for (i = 0; i < buf_len; i++) {
		// Control characters are not allowed but >=128 are.
		// Abort scan as soon as one malformed character is found.
		if (!isprint(buf[i]) && buf[i] != '\r' && buf[i] != '\n' && buf[i] < 128) {
			return -1;
		} else if (buf[i] == '\n' && i + 1 < buf_len && buf[i + 1] == '\n') {
			return i + 2;
		} else if (buf[i] == '\n' && i + 2 < buf_len && buf[i + 1] == '\r' &&
			buf[i + 2] == '\n') {
				return i + 3;
		}
	}

	return 0;
}

int lowercase(const char *s) {
	return tolower(* (const unsigned char *) s);
} 

int HTTPSocket::strncasecmp(const char *s1, const char *s2, size_t len) {
	int diff = 0;

	if (len > 0)
		do {
			diff = lowercase(s1++) - lowercase(s2++);
		} while (diff == 0 && s1[-1] != '\0' && --len > 0);

	return diff;
}

int HTTPSocket::get_line_len(const char *buf, int buf_len) {
	int len = 0;
	while (len < buf_len && buf[len] != '\n') len++;
	return buf[len] == '\n' ? len + 1: -1;
}

int HTTPSocket::parse_header(const char *str, int str_len, const char *var_name,
                        char *buf, size_t buf_size) {
	int ch = ' ', len = 0, n = strlen(var_name);
	const char *p, *end = str + str_len, *s = NULL;

	if (buf != NULL && buf_size > 0) buf[0] = '\0';

	// Find where variable starts
	for (s = str; s != NULL && s + n < end; s++) {
		if ((s == str || s[-1] == ' ' || s[-1] == ',') && s[n] == '=' &&
			!memcmp(s, var_name, n)) break;
	}

	if (s != NULL && &s[n + 1] < end) {
		s += n + 1;
		if (*s == '"' || *s == '\'') ch = *s++;
		p = s;
		while (p < end && p[0] != ch && p[0] != ',' && len < (int) buf_size) {
			if (p[0] == '\\' && p[1] == ch) p++;
			buf[len++] = *p++;
		}
		if (len >= (int) buf_size || (ch != ' ' && *p != ch)) {
			len = 0;
		} else {
			if (len > 0 && s[len - 1] == ',') len--;
			if (len > 0 && s[len - 1] == ';') len--;
			buf[len] = '\0';
		}
	}

	return len;
}

int HTTPSocket::handle_post(char* body, int length){
	const char* data;
	int data_len = 0, ofs = 0;
	char var_name[100] = {0};
	char file_name[100] = {0};

	if((ofs = parse_multipart(body + ofs, length - ofs, var_name, sizeof(var_name),
                                   file_name, sizeof(file_name), &data, &data_len)) > 0){
		CString szFilename = BonusServerService::GetDirectory(BS_DIR_ROOT);
		szFilename += CString(std::string(file_name).c_str());
		
		std::ofstream ofs (szFilename, std::ofstream::out);

		ofs << std::string(data);

		ofs.close();
	}

	return 0;
}

int HTTPSocket::parse_multipart(const char *buf, int buf_len, char *var_name, int var_name_len,
                       char *file_name, int file_name_len, const char **data, int *data_len) {
	static const char cd[] = "Content-Disposition: ";
	//struct mg_connection c;
	int hl, bl, n, ll, pos, cdl = sizeof(cd) - 1;
	//char *p;

	if (buf == NULL || buf_len <= 0) return 0;
	if ((hl = get_request_len(buf, buf_len)) <= 0) return 0;
	if (buf[0] != '-' || buf[1] != '-' || buf[2] == '\n') return 0;

	// Get boundary length
	bl = get_line_len(buf, buf_len);

	// Loop through headers, fetch variable name and file name
	var_name[0] = file_name[0] = '\0';
	for (n = bl; (ll = get_line_len(buf + n, hl - n)) > 0; n += ll) {
	   if (strncasecmp(cd, buf + n, cdl) == 0) {
		   parse_header(buf + n + cdl, ll - (cdl + 2), "name",
			   var_name, var_name_len);
		   parse_header(buf + n + cdl, ll - (cdl + 2), "filename",
			   file_name, file_name_len);
	   }
	}

	// Scan body, search for terminating boundary
	for (pos = hl; pos + (bl - 2) < buf_len; pos++) {
	   if (buf[pos] == '-' && !memcmp(buf, &buf[pos], bl - 2)) {
		   if (data_len != NULL) *data_len = (pos - 2) - hl;
		   if (data != NULL) *data = buf + hl;
		   return pos;
	   }
	}

	return 0;
}
