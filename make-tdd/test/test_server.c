#include "mock.h"
#include "mocksystem.h"
#include "server.h"
#include <check.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/socket.h>

#define TEST_PORT 5150
#define SOCKET_FD 7

bool callback_called = false;
int callback_called_with = -1;

void setup(void) {
    mock_init();
    system_mock_init();
    socket_will_return(SOCKET_FD);
    bind_will_return(0);
    listen_will_return(0);
    select_will_return(0);

    callback_called = false;
    callback_called_with = -1;
}

void teardown(void) {}

void test_callback(int fd) {
    callback_called = true;
    callback_called_with = fd;
}

START_TEST(makeSocket_byDefault_createsInternetStreamSocket) {
    make_socket(TEST_PORT);

    ck_assert_int_eq(PF_INET, socket_called_with_domain());
    ck_assert_int_eq(SOCK_STREAM, socket_called_with_type());
}
END_TEST

START_TEST(makeSocket_byDefault_returnsFdFromSocket) {
    ck_assert_int_eq(SOCKET_FD, make_socket(TEST_PORT));
}
END_TEST

START_TEST(makeSocket_onError_ExitsWithError) {
    socket_will_return(-1);
    make_socket(TEST_PORT);
}
END_TEST

START_TEST(makeSocket_byDefault_bindsSocketToSpecifiedPortOnAllInterfaces) {
    make_socket(TEST_PORT);

    ck_assert_int_eq(SOCKET_FD, bind_called_with_socket());
    ck_assert_int_eq(htons(TEST_PORT), bind_called_with_port());
    ck_assert_int_eq(AF_INET, bind_called_with_family());
    ck_assert_int_eq(INADDR_ANY, bind_called_with_address());
}
END_TEST

START_TEST(makeSocket_whenBindFails_exitsWithError) {
    bind_will_return(-1);
    make_socket(TEST_PORT);
}
END_TEST

START_TEST(makeSocket_byDefault_listensWithBackLogOfOneConnection) {
    make_socket(TEST_PORT);

    ck_assert_int_eq(SOCKET_FD, listen_called_with_socket());
    ck_assert_int_eq(1, listen_called_with_backlog());
}
END_TEST

START_TEST(makeSocket_whenListenFails_exitsWithError) {
    listen_will_return(-1);
    make_socket(TEST_PORT);
}
END_TEST

//
// Listener Tests
//

START_TEST(listener_byDefault_addedSocketToFdSet) {
    fd_set *actual = NULL;
    fd_set read_set;
    FD_SET(SOCKET_FD, &read_set);
    loop(&read_set, test_callback);

    actual = select_called_with_readfds();
    ck_assert_int_ne(0, FD_ISSET(SOCKET_FD, actual));
}
END_TEST

START_TEST(listener_whenSelectFails_exitsWithError) {
    select_will_return(-1);
    fd_set read_set;
    FD_SET(SOCKET_FD, &read_set);
    loop(&read_set, test_callback);
}
END_TEST

START_TEST(listener_byDefault_callsAcceptOnSetFds) {
    int expected = SOCKET_FD + 1;
    select_will_set_readfd(1, expected);
    fd_set read_set;
    FD_SET(SOCKET_FD, &read_set);
    loop(&read_set, test_callback);
    ck_assert_int_eq(expected, accept_called_with_socket());
}
END_TEST

START_TEST(listener_byDefault_callsCallbackWithAcceptFd) {
    int expected = SOCKET_FD - 1;
    accept_will_return(expected);
    fd_set read_set;
    FD_SET(SOCKET_FD, &read_set);
    loop(&read_set, test_callback);
    ck_assert_int_eq(expected, callback_called_with);
}
END_TEST

TCase *tcase_server(void) {
    TCase *tc;

    tc = tcase_create("socket");
    tcase_add_checked_fixture(tc, setup, teardown);

    tcase_add_test(tc, makeSocket_byDefault_createsInternetStreamSocket);
    tcase_add_test(tc, makeSocket_byDefault_returnsFdFromSocket);
    tcase_add_exit_test(tc, makeSocket_onError_ExitsWithError, EXIT_FAILURE);
    tcase_add_test(
        tc, makeSocket_byDefault_bindsSocketToSpecifiedPortOnAllInterfaces);
    tcase_add_exit_test(tc, makeSocket_whenBindFails_exitsWithError,
                        EXIT_FAILURE);
    tcase_add_test(tc, makeSocket_byDefault_listensWithBackLogOfOneConnection);
    tcase_add_exit_test(tc, makeSocket_whenListenFails_exitsWithError,
                        EXIT_FAILURE);

    return tc;
}

TCase *tcase_listener(void) {
    TCase *tc;

    tc = tcase_create("listener");
    tcase_add_checked_fixture(tc, setup, teardown);
    tcase_add_test(tc, listener_byDefault_addedSocketToFdSet);
    tcase_add_exit_test(tc, listener_whenSelectFails_exitsWithError,
                        EXIT_FAILURE);
    tcase_add_test(tc, listener_byDefault_callsAcceptOnSetFds);
    tcase_add_test(tc, listener_byDefault_callsCallbackWithAcceptFd);

    return tc;
}

Suite *suite_server(void) {
    Suite *s;

    s = suite_create("server");
    suite_add_tcase(s, tcase_server());
    suite_add_tcase(s, tcase_listener());

    return s;
}