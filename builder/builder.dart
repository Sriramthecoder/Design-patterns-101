// The Product
class User {
  final String name;
  final int age;
  final String? email;
  final String? address;

  // Private constructor that takes the builder
  User._builder(UserBuilder builder)
      : name = builder.name!,
        age = builder.age!,
        email = builder.email,
        address = builder.address;

  @override
  String toString() {
    return 'User(name: $name, age: $age, email: $email, address: $address)';
  }
}

// The Builder
class UserBuilder {
  String? name;
  int? age;
  String? email;
  String? address;

  UserBuilder setName(String name) {
    this.name = name;
    return this;
  }

  UserBuilder setAge(int age) {
    this.age = age;
    return this;
  }

  UserBuilder setEmail(String email) {
    this.email = email;
    return this;
  }

  UserBuilder setAddress(String address) {
    this.address = address;
    return this;
  }

  User build() {
    if (name == null || age == null) {
      throw Exception("Name and age are required!");
    }
    return User._builder(this);
  }
}

void main() {
  var user = UserBuilder()
      .setName("Alice")
      .setAge(28)
      .setEmail("alice@example.com")
      .setAddress("New York")
      .build();

  print(user);
}
