#ifndef SAVE_H_
# define SAVE_H_

void write_vector(feature *begin, size_t len, char *path);
feature* read(char *path,size_t nbfeature);

#endif /* !SAVE_H_ */
