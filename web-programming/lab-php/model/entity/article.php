<?php 
    class Article implements JsonSerializable {
        private $title;
        private $authorId;
        private $text;
        private $date;
        private $categoryId;

        public function __construct($title, $authorId, $text, $date, $categoryId) {
            $this->title = $title;
            $this->authorId = $authorId;
            $this->text = $text;
            $this->date = $date;
            $this->categoryId = $categoryId;
        }

        public function jsonSerialize() {
            return get_object_vars($this);
        }
    }
?>