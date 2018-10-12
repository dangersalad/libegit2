#include "egit.h"

#ifndef EGIT_BRANCH_H
#define EGIT_BRANCH_H

EGIT_DEFUN(branch_create, emacs_value _repo, emacs_value _name, emacs_value _commitish, emacs_value _force);
EGIT_DEFUN(branch_create_from_annotated, emacs_value _repo, emacs_value _name, emacs_value _commitish, emacs_value _force);
EGIT_DEFUN(branch_delete, emacs_value _repo, emacs_value _branch);
EGIT_DEFUN(branch_is_checked_out, emacs_value _repo, emacs_value _branch);
EGIT_DEFUN(branch_is_head, emacs_value _repo, emacs_value _branch);
EGIT_DEFUN(branch_lookup, emacs_value _repo, emacs_value _branch, emacs_value _type);


#endif /* EGIT_BRANCH_H */
