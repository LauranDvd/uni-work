using asp_net_lab.Models.Domain;

namespace asp_net_lab.Models
{
    public class ArticleViewModel
    {
        public IEnumerable<Article> Articles { get; set; }
        public IEnumerable<Category> Categories { get; set; }
    }
    
}
