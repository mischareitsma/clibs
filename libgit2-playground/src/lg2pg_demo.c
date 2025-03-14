#include <git2.h>
#include <stdlib.h>
#include <stdio.h>

void error(int error_code);
void print_parents(git_commit *commit);

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

	long long ref_long = 0;
	for (int i = 0; i < 20; i++) {
		printf("The char: %d\n", oid.id[i]);
		ref_long += oid.id[i];
		ref_long *= 32;
	}

	char *hex = git_oid_tostr_s(&oid);

	printf("git oid long: %lld\n", ref_long);
	printf("Hex form: %s\n", hex);

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

	printf("Going to walk through commits form HEAD to end.\n");
	print_parents(commit);

	git_libgit2_shutdown();
}

void error(int error_code)
{
	const git_error *err = git_error_last();
	printf("Error %d%d: %s\n", error_code, err->klass, err->message);
	exit(error_code);
}

void print_parents(git_commit *commit) {
	const git_oid *oid = git_commit_id(commit);
	char shortsha[10] = {0};
	git_oid_tostr(shortsha, 9, oid);

	const char *commit_summary = git_commit_summary(commit);

	printf("Commit (%s): %s\n", shortsha, commit_summary);

	unsigned int count = git_commit_parentcount(commit);

	git_commit *commits[count];

	for (unsigned int i=0; i < count; i++) {
		const git_oid *parent_oid = git_commit_parent_id(commit, i);
		git_commit *parent = NULL;
		int error_code = git_commit_parent(&parent, commit, i);
		if (error_code < 0) error(error_code);

		commits[i] = parent;

		git_oid_tostr(shortsha, 9, parent_oid);
		const char *parent_summary = git_commit_summary(parent);
		printf("Parent commit(%s): %s\n", shortsha, parent_summary);
	}
	printf("\n");

	// for (unsigned int i = 0; i < count; i++) {
	// 	print_parents(commits[i]);
	// }
}