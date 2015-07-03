// Here are the main codes for http message parser

if ( gets( line, line_len, BODY_LEN/*sizeof(line)*/ ) == NULL )
{
	break;
}
// first line contains method, file requested and protocol version
if ( sscanf_s( line, "%[^ ] %[^ ] %[^ ]", method, sizeof(method), path, sizeof(path), protocol, sizeof(protocol) ) != 3 )
{
	send_error( 400, "Bad Request", (char*) 0, "Can't parse request." );
	break;
}

is_upload_file = false;
char* tmpbody = body;
// remaining request attributes
while ( gets( line, line_len, BODY_LEN/*sizeof(line)*/ ) != NULL )
{
	// look for end of attributes
	//if ( strcmp( line, "\n" ) == 0 || strcmp( line, CRLF ) == 0 )
	//	break;
	// Connection:
	// Authorization:
	// Host:
	if ( strncmp( line, "Host:", 5 ) == 0 )
	{
		strncpy_s(m_strHost, 100, line + 5, sizeof(m_strHost)-1);
	}
	else if ( strncmp( line, "Connection:", 11 ) == 0 )
	{
		if(strstr(line, "Keep-Alive")) 
			m_bKeepAlive = true;
	}
	else if ( strncmp( line, "Authorization:", 14 ) == 0 )
	{
		sscanf_s( line, "Authorization: %[^ ] %[^ ]", m_strAuthProtocol, sizeof(m_strAuthProtocol), m_strAuthorization, sizeof(m_strAuthorization));
	}
	else if ( strncmp(line, "Content-Type: multipart/form-data", 33) == 0 )
	{
		sscanf_s( line, "%*s %*s boundary=%*[-]%s", boundary, sizeof(boundary));
		is_upload_file = true;
	}
	else if ( strncmp(line, "Content-Disposition: ", 21) == 0)
	{
		sscanf_s( line, "%*s %*s %*s filename=\"%[^\"]\"", file_name, sizeof(file_name));
		const char* pslash = strrchr(file_name, '\\');
		if (pslash != NULL){
			pslash += 1;
			memmove(file_name, pslash, strlen(pslash)+1);
		}
		continue;
	}
	else if (is_upload_file && !strncmp(line, "---", 3) && strstr(line, boundary)) // To find the boundary
	{
		is_boundary = !is_boundary;
		continue;
	}
	
	// copy file content from the http body
	if (is_boundary && line_len >= 1 && strncmp(line, "Content-Type:", 13)){
		assert(line_len < BODY_LEN - body_len);

		memcpy_s(tmpbody, BODY_LEN - body_len, line, line_len);
		tmpbody += line_len;
		body_len += line_len;
	}

	memset(line, '\0', BODY_LEN*sizeof(char));
}
