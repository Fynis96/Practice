import scrapy
from ebookscraper.items import EbookscraperItem
from scrapy.loader import ItemLoader

class EbookSpider(scrapy.Spider):
    name = 'ebook'
    start_urls = ['https://books.toscrape.com']
    cols = ['Title', 'Price']
    
    def __init__(self):
        super().__init__()
        self.page_count = 1
        self.total_pages = 4
        
    def start_request(self):
        base_url = "https://books.toscrape.com"
        
        while self.page_count <= self.total_pages:
            yield scrapy.Request(
                f"{base_url}/page-{self.page_count}.html"
            )
            self.page_count += 1
        
    def parse(self, response):
        ebooks = response.css('article.product_pod')
        
        for ebook in ebooks:
            loader = ItemLoader(item=EbookscraperItem(), selector=ebook)
            
            loader.add_css('title', 'h3 a::attr(title)')
            loader.add_css('price', 'p.price_color::text')
            
            yield loader.load_item()