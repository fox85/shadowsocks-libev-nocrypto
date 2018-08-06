#include <linux/bpf.h>
#include "bpf_helpers.h"

int _version SEC("version") = 1;

#define bpf_printk(fmt, ...)					\
({								\
	       char ____fmt[] = fmt;				\
	       bpf_trace_printk(____fmt, sizeof(____fmt),	\
				##__VA_ARGS__);			\
})

SEC("sk_skb_parse_prog")
int sk_skb_parse(struct __sk_buff *skb)
{
	return skb->len;
}

char _license[] SEC("license") = "GPL";
