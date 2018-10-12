(ert-deftest branch-create ()
  (with-temp-dir path
                 (init)
                 (commit-change "test" "content")
                 (let ((repo (libgit-repository-open path)))
                   (should (libgit-branch-create repo "new-branch" "HEAD"))
                   (should-error (libgit-branch-create repo "new-branch" "HEAD"))))
  (with-temp-dir path
                 (init)
                 (commit-change "test" "content")
                 (run "git" "branch" "second")
                 (run "git" "checkout" "second")
                 (commit-change "test2" "content2")
                 (let ((repo (libgit-repository-open path)))
                   (should-error (libgit-branch-create repo "master" "second"))
                   (should (libgit-branch-create repo "master" "second" t)))))

(ert-deftest branch-create-from-annotated ()
  (with-temp-dir path
                 (init)
                 (commit-change "test" "content")
                 (let ((repo (libgit-repository-open path)))
                   (should (libgit-branch-create-from-annotated repo "new-branch" "HEAD"))
                   (should-error (libgit-branch-create-from-annotated repo "new-branch" "HEAD"))))
  (with-temp-dir path
                 (init)
                 (commit-change "test" "content")
                 (run "git" "branch" "second")
                 (run "git" "checkout" "second")
                 (commit-change "test2" "content2")
                 (let ((repo (libgit-repository-open path)))
                   (should-error (libgit-branch-create-from-annotated repo "master" "second"))
                   (should (libgit-branch-create-from-annotated repo "master" "second" t)))))

(ert-deftest branch-delete ()
  (with-temp-dir path
                 (init)
                 (commit-change "test" "content")
                 (run "git" "branch" "second")
                 (let ((repo (libgit-repository-open path)))
                   (should-error (libgit-branch-delete repo "master"))
                   (should (libgit-branch-delete repo "second")))))

(ert-deftest branch-is-checked-out ()
  (with-temp-dir path
                 (init)
                 (commit-change "test" "content")
                 (run "git" "branch" "second")
                 (let ((repo (libgit-repository-open path)))
                   (should (libgit-branch-is-checked-out repo "master"))
                   (should-not (libgit-branch-is-checked-out repo "second")))))

(ert-deftest branch-is-head ()
  (with-temp-dir path
                 (init)
                 (commit-change "test" "content")
                 (run "git" "branch" "second")
                 (let ((repo (libgit-repository-open path)))
                   (should (libgit-branch-is-head repo "master"))
                   (should-not (libgit-branch-is-head repo "second")))))

(ert-deftest branch-lookup ()
  (with-temp-dir path
                 (init)
                 (commit-change "test" "content")
                 (run "git" "branch" "second")
                 (let ((repo (libgit-repository-open path)))
                   (should (libgit-lookup repo "master"))
                   (should (libgit-lookup repo "second"))
                   (should (libgit-lookup repo "second"))
                   (should-error (libgit-lookup repo "third"))
                   (should-error (libgit-lookup repo "master" t)))))

