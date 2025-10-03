from abc import ABC, abstractmethod

# Define the abstract class for the ComputeService products
class ComputeService(ABC):
    @abstractmethod
    def start_instance(self):
        pass

# Define the abstract class for StorageService products
class StorageService(ABC):
    @abstractmethod
    def upload_file(self, filename: str):
        pass
    
# Define the concrete class with the products for Amazon
class EC2(ComputeService):
    def start_instance(self):
        print("Starting EC2 instance in the AWS...")
    
class S3(StorageService): 
    def upload_file(self,filename: str):
        print(f"Uploading {filename} to the AWS S3...")
        
# Define the concrete class with the products for Azure
class AzureVM(ComputeService):
    def start_instance(self):
        print("Starting AzureVM instance in the Azure...")
    
class BlobStorage(StorageService): 
    def upload_file(self,filename: str):
        print(f"Uploading {filename} to the BlobStorage...")
        
# Define the concrete class with the products for Google
class ComputeEngine(ComputeService):
    def start_instance(self):
        print("Starting ComputeEngine instance in the Google...")
    
class CloudStorage(StorageService): 
    def upload_file(self, filename: str):
        print(f"Uploading {filename} to the Google CloudStorage...")
        
        
# CloudFactory 
# Create a CloudFactory abstract class
class CloudFactory(ABC):
    @abstractmethod
    def create_compute_service(self) -> ComputeService:
        pass
    @abstractmethod
    def create_storage_service(self) -> StorageService:
        pass

# Create a concrete class for the amazon cloud factory
class AWSFactory(CloudFactory):
    def create_compute_service(self) -> ComputeService:
        return EC2()
    def create_storage_service(self) -> StorageService:
        return S3()
    
# Create a concrete class for the azure cloud factory
class AzureFactory(CloudFactory):
    def create_compute_service(self) -> ComputeService:
        return AzureVM()
    def create_storage_service(self) -> StorageService:
        return BlobStorage()
    
# Create a concrete class for the google cloud factory
class GCPFactory(CloudFactory):
    def create_compute_service(self) -> ComputeService:
        return ComputeEngine()
    def create_storage_service(self) -> StorageService:
        return CloudStorage()
    
    
# -------- Client --------
class CloudApplication:
    def __init__(self, factory: CloudFactory):
        self.compute = factory.create_compute_service()
        self.storage = factory.create_storage_service()

    def deploy(self, filename: str):
        self.compute.start_instance()
        self.storage.upload_file(filename)


# -------- Usage --------
if __name__ == "__main__":
    print("=== Deploying to AWS ===")
    aws_app = CloudApplication(AWSFactory())
    aws_app.deploy("app.zip")

    print("\n=== Deploying to Azure ===")
    azure_app = CloudApplication(AzureFactory())
    azure_app.deploy("data.csv")

    print("\n=== Deploying to GCP ===")
    gcp_app = CloudApplication(GCPFactory())
    gcp_app.deploy("model.pkl")
    
    