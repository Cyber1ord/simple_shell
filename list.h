#ifndef MY_HEADER_FILE_H
#define MY_HEADER_FILE_H

// Declare the struct
typedef struct liststr {
	char *str;
	struct liststr *next;
} list_t;

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

// Declare the functions that use the struct
list_t *add_node(list_t **head, const char *str, int index);
list_t *add_node_end(list_t **head, const char *str, int index);
size_t print_list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head);
size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with(list_t *head, char *str, char c);
ssize_t get_node_index(list_t *head, list_t *node);

#endif /* MY_HEADER_FILE_H */

