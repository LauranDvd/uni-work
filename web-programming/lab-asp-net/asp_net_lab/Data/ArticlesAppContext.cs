using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using asp_net_lab.Models.Domain;

namespace asp_net_lab
{
    public class ArticlesAppContext : DbContext
    {
        public ArticlesAppContext (DbContextOptions<ArticlesAppContext> options)
            : base(options)
        {
        }

        public DbSet<asp_net_lab.Models.Domain.Article> Article { get; set; } = default!;
        public DbSet<asp_net_lab.Models.Domain.Author> Author { get; set; } = default!;
        public DbSet<asp_net_lab.Models.Domain.Category> Category { get; set; } = default!;
    }
}
