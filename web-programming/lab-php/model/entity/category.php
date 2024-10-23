<?php 
    class Category implements JsonSerializable {
        private $id;
        private $name;

        public function __construct($id, $name) {
            $this->id = $id;
            $this->name = $name; 
        }


        public function jsonSerialize() {
            return get_object_vars($this);
        }
    }
?>