using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using asp_net_lab;
using asp_net_lab.Models.Domain;
using asp_net_lab.Models;
using Microsoft.AspNetCore.Authorization;

namespace asp_net_lab.Controllers
{
    [Authorize]
    public class ArticlesController : Controller
    {
        private readonly ArticlesAppContext _context;

        public ArticlesController(ArticlesAppContext context)
        {
            _context = context;
        }

        public async Task<IActionResult> Index(string categoryName = "")
        {
            var categories = await _context.Category.ToListAsync();

            // If no category is specified, retrieve all articles
            var articlesQuery = _context.Article.Include(a => a.Author).Include(a => a.Category);
            if (!string.IsNullOrEmpty(categoryName))
            {
                articlesQuery = (Microsoft.EntityFrameworkCore.Query.IIncludableQueryable<Article, Category>)articlesQuery.Where(article => article.Category.Name == categoryName);
            }

            var articles = await articlesQuery.ToListAsync();

            var viewModel = new ArticleViewModel
            {
                Articles = articles,
                Categories = categories
            };

            return View(viewModel);
        }

        public async Task<IActionResult> FilteredByCategory(string selectedCategory, DateTime? startDate, DateTime? endDate)
        {
            var query = _context.Article.Include(a => a.Author).Include(a => a.Category).AsQueryable();

            if (!string.IsNullOrEmpty(selectedCategory))
            {
                query = query.Where(a => a.Category.Name == selectedCategory);
            }

            if (startDate.HasValue)
            {
                query = query.Where(a => a.Date >= startDate.Value);
            }

            if (endDate.HasValue)
            {
                query = query.Where(a => a.Date <= endDate.Value);
            }

            var filteredArticles = await query.ToListAsync();

            return PartialView("_ArticlesList", filteredArticles);
        }

        // GET: Articles/Details/5
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var article = await _context.Article
                .Include(a => a.Author)
                .Include(a => a.Category)
                .FirstOrDefaultAsync(m => m.Id == id);
            if (article == null)
            {
                return NotFound();
            }

            return View(article);
        }

        // GET: Articles/Create
        public IActionResult Create()
        {
            //ViewData["AuthorId"] = new SelectList(_context.Set<Author>(), "Id", "Id");
            ViewData["Category"] = new SelectList(_context.Set<Category>(), "Id", "Name");
            ViewData["Author"] = new SelectList(_context.Set<Author>(), "Id", "Name");
            return View();
        }

        // POST: Articles/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [Authorize(Roles = "admin")]
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("Id,Title,AuthorId,Text,Date,CategoryId")] Article article)
        {
            if (ModelState.IsValid)
            {
                _context.Add(article);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            var errors = ModelState.Values.SelectMany(v => v.Errors)
                                  .Select(e => e.ErrorMessage);
            var errorMessage = "ModelState is not valid: " + string.Join("; ", errors);
            throw new Exception(errorMessage);
        }

        // GET: Articles/Edit/5
        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var article = await _context.Article.FindAsync(id);
            if (article == null)
            {
                return NotFound();
            }
            ViewData["AuthorId"] = new SelectList(_context.Set<Author>(), "Id", "Name", article.AuthorId);
            ViewData["CategoryId"] = new SelectList(_context.Set<Category>(), "Id", "Name", article.CategoryId);
            return View(article);
        }

        // POST: Articles/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [Authorize(Roles = "admin")]
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int id, [Bind("Id,Title,AuthorId,Text,Date,CategoryId")] Article article)
        {
            if (id != article.Id)
            {
                return NotFound();
            }

            if (!ModelState.IsValid)
                throw new Exception("Bad inputs");

            try
            {
                _context.Update(article);
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!ArticleExists(article.Id))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }
            return RedirectToAction(nameof(Index));
        }

        // GET: Articles/Delete/5
        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var article = await _context.Article
                .Include(a => a.Author)
                .Include(a => a.Category)
                .FirstOrDefaultAsync(m => m.Id == id);
            if (article == null)
            {
                return NotFound();
            }

            return View(article);
        }

        // POST: Articles/Delete/5
        [Authorize(Roles = "admin")]
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(int id)
        {
            var article = await _context.Article.FindAsync(id);
            if (article != null)
            {
                _context.Article.Remove(article);
            }

            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool ArticleExists(int id)
        {
            return _context.Article.Any(e => e.Id == id);
        }
    }
}
