#define DEBUG

#define log(fmt, ...) printf(fmt, ##__VA_ARGS__)

#ifdef DEBUG
#define logd(fmt, ...) log("[dbg] [%s|%d]: "fmt"\n", __func__, __LINE__, ##__VA_ARGS__)
#else
#define logd(fmt, ...) do {} while (0)
#endif /* DEBUG */

#define loge(fmt, ...) log("[ERR] [%s|%d]: "fmt"\n", __func__, __LINE__, ##__VA_ARGS__)
