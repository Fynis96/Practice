from openpyxl import Workbook
from itemadapter import ItemAdapter


class EbookscraperPipeline:
    
    def open_spider(self, spider):
        self.workbook = Workbook()
        self.sheet = self.workbook.active
        self.sheet.title = 'ebooks'
        self.sheet.append(spider.cols)
    
    def process_item(self, item, spider):
        self.sheet.append([ item['title'], item['price'] ])
        
        return item
    
    def close_spider(self, spider):
        self.workbook.save('ebooks.xlsx')
