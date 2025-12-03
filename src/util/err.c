#include <util/util.h>

static size_t
	hdr_size()
{
	static size_t hdr_size;

	if (!hdr_size)
	{
		hdr_size = sizeof(struct s_err_str_hdr);
		if (hdr_size < 16)
			hdr_size = 16;
	}
	return (hdr_size);
}

t_err_str
	err(t_err_str err, const char *str)
{
	struct s_err_str_hdr	*hdr = (struct s_err_str_hdr*)(err - hdr_size());
	char					*buf;
	const size_t			len = ft_strlen(str);

	if (!err || !err[0])
	{
		buf = xmalloc(hdr_size() + len);
		*((struct s_err_str_hdr *)buf) = (struct s_err_str_hdr){len, len};
		return (buf + hdr_size());
	}
	while (hdr->capacity <= hdr->size + len + 1)
		hdr->capacity = hdr->capacity * 2 + !hdr->capacity * 16;
	buf = xmalloc(hdr_size() + hdr->capacity);
	*((struct s_err_str_hdr *)buf) = (struct s_err_str_hdr){hdr->size + len,
		hdr->capacity};
	ft_memcpy(buf + hdr_size(), err, hdr->size);
	ft_memcpy(buf + hdr_size() + hdr->size, str, len);
	buf[hdr_size() + hdr->size + len] = 0;
	free(err);
	return (buf + hdr_size());

}

void
	err_free(t_err_str err)
{
	if (!err || !err[0])
		return ;
	free(err - hdr_size());
}
