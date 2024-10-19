namespace asp_net_lab.Models.Domain
{
    public class Author
    {
        public int Id { get; set; }
        public string Name { get; set; }

        public ICollection<Article> Articles { get; set; } = new List<Article>();
    }
}
