#include <git2.h>
#include <stdlib.h>
#include <stdio.h>

void error(int error_code);

void demo_libgit2(const char* const repo_location) {
	git_libgit2_init();

	git_repository *repo = NULL;
	int error_code = git_repository_open(&repo, repo_location);

	if (error_code < 0) error(error_code);

	printf("Opened repository %s\n\n", repo_location);

	// Get HEAD:
	git_oid oid;
	error_code = git_reference_name_to_id(&oid, repo, "HEAD");
	if (error_code < 0) error(error_code);

	char shortsha[10] = {0};
	git_oid_tostr(shortsha, 9, &oid);
	printf("The short SHA for the HEAD is %s\n\n", shortsha);

	git_commit *commit = NULL;
	error_code = git_commit_lookup(&commit, repo, &oid);
	if (error_code < 0) error(error_code);

	const char *message = git_commit_message(commit);
	const char *summary = git_commit_summary(commit);

	printf("The message of the HEAD commit:\n%s\n\n", message);
	printf("The summary of the HEAD commit:\n%s\n\n", summary);

	git_libgit2_shutdown();
}

void error(int error_code)
{
	const git_error *err = git_error_last();
	printf("Error %d%d: %s\n", error_code, err->klass, err->message);
	exit(error_code);
}