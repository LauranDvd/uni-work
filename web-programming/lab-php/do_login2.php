<?php
header('Access-Control-Allow-Origin: *');

require_once('repository/user_repository.php');

session_start();
$username = $_POST["user-input"];
$password = $_POST["password"];

$userRepository = new UserRepository();
$obtainedUser = $userRepository->getByUsernamePassword($username, $password);
if ($obtainedUser != NULL) {
    $_SESSION['userId'] = $obtainedUser['userId'];
    echo json_encode("good credentials. userid=" . $obtainedUser['userId']);
    // header('Location: home.php');
} else {
    // header('Location: login.html');
    echo "bad credentials";
}
