<?php 
    class User implements JsonSerializable {
        private $username;
        private $password;
        private $fullName;
        private $isAdmin;

        public function __construct($username, $password, $fullName, $isAdmin) {
            $this->username = $username;
            $this->password = $password;
            $this->fullName = $fullName;
            $this->isAdmin = $isAdmin;
        }

        public function jsonSerialize() {
            return get_object_vars($this);
        }
    }

?>