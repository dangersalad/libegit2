#include "interface.h"
#include "egit-repository.h"


EGIT_DOC(branch_create, "REPO NAME COMMITISH FORCE", "Create a new branch in REPO named NAME at COMMITISH and return the refernce to it. If FORCE is non-nil, force creation of the branch.");
emacs_value egit_branch_create(emacs_env *env, emacs_value _repo, emacs_value _name, emacs_value _commitish, emacs_value _force)
{
    EGIT_ASSERT_REPOSITORY(_repo);
    EGIT_ASSERT_STRING(_commitish);

    git_repository *repo = EGIT_EXTRACT(_repo);
    EGIT_ASSERT_STRING(_name);

    
    git_reference *targetRef;
    int retval;
    {
      char *commitish = EGIT_EXTRACT_STRING(_commitish);
      retval = git_reference_dwim(&targetRef, repo, commitish);
      free(commitish);
    }
    EGIT_CHECK_ERROR(retval);
    
    const git_oid *oid = git_reference_target(targetRef);
    
    git_commit *commit;
    retval = git_commit_lookup(&commit, repo, oid);
    EGIT_CHECK_ERROR(retval);

    git_reference *ref;
    {
        char *name = EGIT_EXTRACT_STRING(_name);
        bool force = EGIT_EXTRACT_BOOLEAN(_force);
        retval = git_branch_create(&ref, repo, name, commit, force);
        free(name);
    }
    EGIT_CHECK_ERROR(retval);

    return egit_wrap(env, EGIT_REFERENCE, ref);
}

EGIT_DOC(branch_create_from_annotated, "REPO NAME COMMITISH FORCE", "Create a new branch in REPO named NAME at annotated commit COMMITISH and return the refernce to it. If FORCE is non-nil, force creation of the branch.");
emacs_value egit_branch_create_from_annotated(emacs_env *env, emacs_value _repo, emacs_value _name, emacs_value _commitish, emacs_value _force)
{
    EGIT_ASSERT_REPOSITORY(_repo);
    EGIT_ASSERT_STRING(_commitish);

    git_repository *repo = EGIT_EXTRACT(_repo);
    EGIT_ASSERT_STRING(_name);

    
    git_reference *targetRef;
    int retval;
    {
      char *commitish = EGIT_EXTRACT_STRING(_commitish);
      retval = git_reference_dwim(&targetRef, repo, commitish);
      free(commitish);
    }
    EGIT_CHECK_ERROR(retval);
    
    const git_oid *oid = git_reference_target(targetRef);
    
    git_annotated_commit *commit;
    retval = git_annotated_commit_lookup(&commit, repo, oid);
    EGIT_CHECK_ERROR(retval);

    git_reference *ref;
    {
        char *name = EGIT_EXTRACT_STRING(_name);
        bool force = EGIT_EXTRACT_BOOLEAN(_force);
        retval = git_branch_create_from_annotated(&ref, repo, name, commit, force);
        free(name);
    }
    EGIT_CHECK_ERROR(retval);

    return egit_wrap(env, EGIT_REFERENCE, ref);
}

EGIT_DOC(branch_delete, "REPO BRANCH", "Delete BRANCH in REPO.");
emacs_value egit_branch_delete(emacs_env *env, emacs_value _repo, emacs_value _branch)
{
    EGIT_ASSERT_REPOSITORY(_repo);
    git_repository *repo = EGIT_EXTRACT(_repo);
    
    EGIT_ASSERT_STRING(_branch);
    
    git_reference *targetRef;
    int retval;
    {
      char *branch = EGIT_EXTRACT_STRING(_branch);
      retval = git_reference_dwim(&targetRef, repo, branch);
      free(branch);
    }
    EGIT_CHECK_ERROR(retval);

    EGIT_CHECK_ERROR(git_reference_is_branch(targetRef));

    retval = git_branch_delete(targetRef);
    EGIT_CHECK_ERROR(retval);

    return em_t;
}
