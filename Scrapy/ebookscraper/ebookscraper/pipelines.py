from pymongo import MongoClient
from itemadapter import ItemAdapter
from dotenv import load_dotenv
import os

load_dotenv()
DBURI = os.getenv('DBURI')


class EbookscraperPipeline:
    
    def open_spider(self, spider):
        
        self.client = MongoClient(
            host=DBURI,
            connect=False
        )
        self.collection = self.client.get_database("ebook").get_collection("travel")
    
    def process_item(self, item, spider):
        self.collection.insert_one(
            ItemAdapter(item).asdict()
        )
        return item
    
    def close_spider(self, spider):
        self.client.close()
