#include <linux/bpf.h>
#include "bpf_helpers.h"

int _version SEC("version") = 1;

struct bpf_map_def SEC("maps") redirect_map = {
	.type = BPF_MAP_TYPE_SOCKMAP,
	.key_size = sizeof(int),
	.value_size = sizeof(int),
	.max_entries = 2,
};

SEC("sk_skb_verdict_prog")
int sk_skb_verdict(struct __sk_buff *skb)
{
	if(skb->local_port == 0xfcfcfcfc)
		return bpf_sk_redirect_map(skb, &redirect_map, 0, 0);
	
	return bpf_sk_redirect_map(skb, &redirect_map, 1, 0);
}

char _license[] SEC("license") = "GPL";
