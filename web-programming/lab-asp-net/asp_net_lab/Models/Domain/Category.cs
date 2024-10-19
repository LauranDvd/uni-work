using System.ComponentModel.DataAnnotations;

namespace asp_net_lab.Models.Domain
{
    public class Category
    {
        public int Id { get; set; }
        [StringLength(20, MinimumLength = 2)]
        public string Name { get; set; }

        public ICollection<Article> Articles { get; set; } = new List<Article>();
    }
}
