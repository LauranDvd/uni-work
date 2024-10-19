using System.ComponentModel.DataAnnotations;

namespace asp_net_lab.Models.Domain
{
    public class Article
    {
        public int Id { get; set; }
        public string Title { get; set; }
        [Display(Name = "Author")]
        public int AuthorId { get; set; }
        [StringLength(10000, MinimumLength = 5)]
        public string Text { get; set; }
        public DateTime Date { get; set; }
		[Display(Name = "Category")]
		public int CategoryId { get; set; }

        public Author? Author { get; set; }
        public Category? Category { get; set; }
    }
}
